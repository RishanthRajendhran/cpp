struct node {
    int key;
    int value;
    node* next;
    node* prev;
};

class LRUCache
{
    private:
    node *root, *leaf;
    map<int, node*> nodeMap;
    int size;
    public:
    //Constructor for initializing the cache capacity with the given value.
    LRUCache(int cap)
    {
        // code here
        root = NULL;
        leaf = NULL;
        nodeMap.clear();
        size = cap;
    }
    
    //Function to return value corresponding to the key.
    int get(int key)
    {
        // your code here
        auto it = nodeMap.find(key);
        if(it != nodeMap.end()) {
            node* curNode = it->second;
            if(curNode->prev) { //Not already the root
                (curNode->prev)->next = curNode->next;
                if(curNode->next) {
                    (curNode->next)->prev = curNode->prev;
                } else {    //The node is a leaf; Make prev node the leaf
                    leaf = curNode->prev;
                }
                curNode->next = root;
                curNode->prev = NULL;
                root->prev = curNode;
                root = curNode;
            }
            return curNode->value;
        }
        return -1;
    }
    
    //Function for storing key-value pair.
    void set(int key, int value)
    {
        auto it = nodeMap.find(key);
        if(it == nodeMap.end()) {
            if(nodeMap.size() >= size && leaf != NULL) {
                node* leafPrev = leaf->prev;
                auto it = nodeMap.find(leaf->key);
                if(it != nodeMap.end()) {
                    nodeMap.erase(it);
                }
                node* curLeaf = leaf;
                delete curLeaf;
                leaf = leafPrev;
                if(leaf) {
                    leaf->next = NULL;
                }
            }
            node* newNode = new node;
            newNode->key = key;
            newNode->value = value;
            newNode->prev = NULL;
            newNode->next = root;
            if(root) {
                root->prev = newNode;
            }
            root = newNode;
            nodeMap.insert(make_pair(key, newNode));
            if(leaf == NULL) {  //This is true only when cache is empty
                    leaf = newNode;
            }
        } else {
            node* curNode = it->second;
            curNode->value = value;
            if(curNode->prev) { //Not already the root
                (curNode->prev)->next = curNode->next;
                if(curNode->next) {
                    (curNode->next)->prev = curNode->prev;
                } else {    //It is the leaf
                    leaf = curNode->prev;
                }
                curNode->prev = NULL;
                curNode->next = root;
                root->prev = curNode;
                root = curNode;
            }
         }
        return;
    }
};