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

    bool is_larger_key(K key1, K key2)
    {
        return key1 > key2;
    }

    Node *head;
    int element_count;

public:
    binary_search_tree()
    {
        this->head = nullptr;
        this->element_count = 0;
    }

    void insert(K key)
    {
        Node *node_to_insert = Node(key, nullptr, nullptr, nullptr);
        K key_to_insert = key;

        Node *trav_parent = nullptr;
        Node *trav = head;
        K trav_key = trav->key;

        while (trav != null)
        {
            if (is_larger_key(key_to_insert, trav_key))
            {
                trav_parent = trav;
                trav = trav->right_child;
                trav_key = trav->key;
            }
            else
            {
                trav_parent = trav;
                trav = trav->left_child;
                trav_key = trav->key;
            }
        }
        // position found, update parent Node's attributes
        if (is_larger_key(key_to_insert, trav_parent->key))
        {
            trav_parent->right_child = node_to_insert;
        }
        else
        {
            trav_parent->left_child = node_to_insert;
        }
        trav = node_to_insert;
        element_count += 1;
    }

    void remove(K key)
    {
    }

    void search(K key)
    {
    }

    K get_min()
    {
    }

    K get_max()
    {
    }
};