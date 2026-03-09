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
    }

    void remove(K key)
    {
    }

    void search(K key)
    {
    }
};