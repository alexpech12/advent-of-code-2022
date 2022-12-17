#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

class Node {
  public:

    Node(Node *parent, string name, int size) {
      this->parent = parent;
      this->name = name;
      this->size = size;
    }

    void addNode(string name, int size) {
      children.emplace(name, Node(this, name, size));
      if (size > 0) {
        increaseSize(size);
      }
    }

    Node* getChild(string name) {
      return &children.at(name);
    }

    Node* getParent() {
      return parent;
    }

    int getSize() {
      return size;
    }

    string getName() {
      return name;
    }

    void increaseSize(int size) {
      this->size += size;
      if (parent) {
        parent->increaseSize(size);
      }
    }

    bool isDir() {
      return !children.empty();
    }

    template<typename Functor>
    void traverse(Functor yield) {
      if (children.size() == 0)
        return;

      for(auto pair : children) {
        auto child = &pair.second;
        yield(child);
        child->traverse(yield);
      }
    }

    int getDepth() {
      auto node = parent;
      int depth = 0;
      while(node) {
        node = node->getParent();
        depth++;
      }
      return depth;
    }

  private:
    unordered_map<string, Node> children;
    Node* parent;
    string name;
    int size = 0;
};

int main(int argc, char *argv[]) {
  ifstream MyFile(argv[1]);

  string line;

  Node tree = Node(NULL, "/", 0);
  Node *cd = &tree;

  getline(MyFile, line); // Discard first cd / line

  while (getline(MyFile, line)) {
    cout << line << endl;

    const char *c_str = line.c_str();

    if (c_str[0] == '$') {
      cout << "Command - ";
      // Command
      if (strncmp(c_str + 2, "cd", 2) == 0) {
        const char *dirName = c_str + 5;
        cout << "Change dir (" << dirName << ") - ";
        // Change directory

        if (strncmp(dirName, "..", 2) == 0) {
          // Go up
          cout << "Going up... ";
          cd = cd->getParent();
        } else {
          cout << "Going down... ";
          cd = cd->getChild(dirName);
        }
      }
    } else {
      // File. Add node.
      cout << "Adding node - ";
      if (strncmp(c_str, "dir", 3) == 0) {
        cout << "Adding dir (" << c_str + 4 << ") - ";
        // Add directory
        cd->addNode(c_str + 4, 0);
      } else {
        // Add file
        int split = line.find(' ');
        cout << "Split location = " << split << ", size str = " << line.substr(0, split) << " - ";
        int size = stoi(line.substr(0, split));
        string name = line.substr(split + 1, line.length());
        cout << "Adding file - Size: " << size << ", Name: " << name;
        cd->addNode(name, size);
      }
    }
    cout << endl;
  }

  // Calculate result
  int sum = 0;
  auto print_size = [&sum](Node *node) mutable {
    cout << (node->isDir() ? "dir " : "file ") << "- Name: " << node->getName() << ", Size: " << node->getSize() << endl;
    cout << "Adding " << node->getSize() << " to " << sum << endl;
    sum += node->getSize();
    cout << "Sum is now " << sum << endl;
  };

  auto sum_small_dirs = [&sum](Node *node) mutable {
    cout << "Checking " << node->getName() << " (size " << node->getSize() << ", isDir " << node->isDir() << ")..." << endl;
    if (node->isDir() && node->getSize() <= 100000) {
      sum += node->getSize();
    }
  };

  auto print_tree = [](Node *node) mutable {
    for(int i = 0; i < node->getDepth(); i++) {
      cout << "   ";
    }
    cout << node->getName() << " (" << (node->isDir() ? "dir" : "file") << ", size=" << node->getSize() << ")\n";
  };

  tree.traverse(print_tree);
  tree.traverse(sum_small_dirs);

  cout << "Sum = " << sum << endl;

  MyFile.close();
}
