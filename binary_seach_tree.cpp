template <typename K>
class binary_search_tree
{
private:
    struct Node
    {
        Node *parent;
        Node *left_child;
        Node *right_child;
        K key;

        Node(K key, Node *parent, Node *left_child, Node *right_child)
        {
            this->key = key;
            this->parent = parent;
            this->left_child = left_child;
            this->right_child = right_child;
        }
    };
    // **************************************************************
    // *** helper methods; private to allow for a clean interface ***
    // **************************************************************

    bool is_larger_key(K key1, K key2)
    {
        return key1 > key2;
    }

    Node *find_parent(K key)
    {
        // return the parent of a given key

        Node *trav = root;
        Node *parent = nullptr;

        while (trav != nullptr)
        {
            parent = trav;

            if (is_larger_key(key, trav->key))
            {
                trav = trav->right_child;
            }
            else
            {
                trav = trav->left_child;
            }
        }
        return parent;
    }

    Node *find_predecessor(Node *target)
    {
        // find and return the node with the largest value in the left subtree of target
        if (target->left_child == nullptr)
        {
            return nullptr;
        }

        Node *trav = target->left_child;

        return get_max_node(trav);
    }

    Node *find_succesor(Node *target)
    {
        // find and return the node with the smallest value in the right subtree of target
        if (target->right_child == nullptr)
        {
            return nullptr;
        }

        Node *trav = target->right_child;

        return get_min_node(trav);
    }

    // binary search tree's attributes
    Node *root;
    int element_count;

public:
    binary_search_tree()
    {
        this->root = nullptr;
        this->element_count = 0;
    }

    void insert(K key)
    {
        Node *node_to_insert = Node(key, nullptr, nullptr, nullptr);

        // search the proper sub-branch of trav
        Node *parent = find_parent(key);

        // only update parent attributes if the insertion is not at the root
        if (parent != nullptr)
        {
            if (is_larger_key(key, parent->key))
            {
                parent->right_child = node_to_insert;
            }
            else
            {
                parent->left_child = node_to_insert;
            }
        }
        else // initialize the root
        {
            root = node_to_insert;
        }
        element_count += 1;
    }

    void remove(K key)
    {
        Node *to_removes_parent = find_parent(key);

        // key does not exist
        if (to_removes_parent == nullptr)
        {
            throw std::invalid_argument("Key does not exist.");
        }

        Node *to_remove;       // determine the node which must be removed, given its parent
        Node *is_parents_left; // the node to delete is the left child of the parent node

        if (to_removes_parent->left_child->key == to_remove->key)
        {
            to_remove = to_removes_parent->left_child;
            is_parents_left = true;
        }
        else
        {
            to_remove = to_removes_parent->right_child;
            is_parents_left = false;
        }

        // case 1: node to delete has no children
        // case 2: node to delete has a predecessor or successor
        // case 3: node to delete has both a predecessor and successor

        // to remove a node, either replace with the largest value in the left subtree (predecessor), or the smallest value in the right subtree (successor)

        // step 1:
        // in the case of a predecessor, update predecessors children to point to the node to deletes children
        // in the case of a successor, update the successors children to point to the node to deletes children
        // in the case of no predecessor or successor, nothing is required

        // step 2:
        // in the case of a predecessor, update the predecessors parent's right child node to nullptr
        // in the case of a successor, update the successors parent's left child node to nullptr
        // in the case of no predecessor or successor, nothing is required

        // step 3:
        // in the case of a predecessor, update the node to removes child pointer to point to the predecessor
        // in the case of a successor, update the node to removes child pointer to point to the successor
        // in the case of no predecessor or successor, update the node to removes child pointer to nullptr

        // step 4:
        // deallocate the memory that was used to store the node which we want to remove

        Node *predecessor = find_predecessor(to_remove);
        Node *predecessors_parent = predecessor->parent;
        Node *successor = find_succesor(to_delete);
        Node *successors_parent = successor->parent;

        if (predecessor != nullptr)
        {
            // make predecessors children = children of node to delete
            predecessor->left_child = to_delete->left_child;
            predecessor->right_child = to_delete->right_child;
            // update the parent of predecessor's child node to nullptr
            predecessors_parent->right_child = nullptr;

            if (is_parents_left) // to remove is the parents left child
            {
                to_removes_parent->left_child = predecessor;
            }
            else // to remove is the parents right child
            {
                // update the parent's child pointer from the node to delete to the predecessor
                to_removes_parent->right_child = predecessor;
            }
        }
        else if (successor != nullptr)
        {
            // make predecessors children = children of node to delete
            successor->left_child = to_delete->left_child;
            successor->right_child = to_delete->right_child;
            // update the parent of predecessor's child node to nullptr
            successors_parent->left_child = nullptr;

            if (is_parents_left) // to remove is the parents left child
            {
                to_removes_parent->left_child = predecessor;
            }
            else // to remove is the parents right child
            {
                // update the parent's child pointer from the node to delete to the predecessor
                to_removes_parent->right_child = predecessor;
            }
        }
        else
        {
            if (is_parents_left)
            {
                to_removes_parent->left_child = nullptr;
            }
            else
            {
                to_removes_parent->right_child = nullptr;
            }
        }
        delete to_remove;
    }

    bool search(K key)
    {
        Node *parent = find_parent(key);

        // parent exists
        if (parent != nullptr)
        {
            if (is_larger_key(key, parent->right_child))
            {
                return key == parent->right_child->key;
            }
            else
            {
                return key == parent->left_child->key;
            }
        }
        // root is the only node
        return key == root->key;
    }

    Node *get_min_node(Node *starting_root)
    {
        if (starting_root == nullptr)
        {
            return std::underflow_error("The given root has no elements associated with it.")
        }

        Node *trav = starting_root;

        while (trav->left_child != nullptr)
        {
            trav = trav->left_child;
        }
        return trav;
    }

    K get_min_val(Node *starting_root)
    {
        return get_min_node(starting_root)->key;
    }

    Node *get_max_node(Node *starting_root)
    {
        if (starting_root == nullptr)
        {
            return std::underflow_error("The given root has no elements associated with it.")
        }

        Node *trav = starting_root;

        while (trav->right_child != nullptr)
        {
            trav = trav->right_child;
        }
        return trav;
    }

    K get_max(Node *starting_root)
    {
        return get_min_node(starting_root)->key;
    }

    Node *get_tree_root()
    {
        return this->root;
    }
};