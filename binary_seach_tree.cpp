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

    // helper methods, private to allow for a clean interface
    bool is_larger_key(K key1, K key2)
    {
        return key1 > key2;
    }

    Node *find_parent(K key)
    {
        // return the parent of the key, for both searching, removal, insertion, etc.

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

        while (trav->right_child != nullptr)
        {
            trav = trav->right_child;
        }
        return trav;
    }

    Node *find_succesor(Node *target)
    {
        // find and return the node with the smallest value in the right subtree of target
        if (target->right_child == nullptr)
        {
            return nullptr;
        }

        Node *trav = target->right_child;

        while (trav->left_child != nullptr)
        {
            trav = trav->left_child;
        }
        return trav;
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
        Node *node_to_insert = Node(key_to_insert, nullptr, nullptr, nullptr);

        // search the proper sub-branch of trav
        Node *parent = find_parent(key_to_insert);

        // only update parent attributes if the insertion is not at the root
        if (parent != nullptr)
        {
            if (is_larger_key(key_to_insert, parent->key))
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
        // key does not exist
        if (!search(key))
        {
            throw std::invalid_argument("Key does not exist.")
        }

        Node *parent = find_parent(key);
        Node *to_delete = nullptr;

        // parent exists
        if (parent != nullptr)
        {
        }
        // root is the only node
        to_delete = root;
        root = nullptr;
        delete to_delete;
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

    K get_min()
    {
        if (root == nullptr)
        {
            return std::underflow_error("The tree is empty");
        }

        Node *trav = root;

        while (trav->left_child != nullptr)
        {
            trav = trav->left_child;
        }
        return trav->key;
    }

    K get_max()
    {
        if (root == nullptr)
        {
            return std::underflow_error("The tree is empty");
        }

        Node *trav = root;

        while (trav->right_child != nullptr)
        {
            trav = trav->right_child;
        }
        return trav->key;
    }
};