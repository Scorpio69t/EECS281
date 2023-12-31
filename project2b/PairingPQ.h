// Project identifier: 9504853406CBAC39EE89AA3AD238AA12CA198043

#ifndef PAIRINGPQ_H
#define PAIRINGPQ_H

#include "Eecs281PQ.h"
#include <queue>
#include <deque>
#include <utility>

// A specialized version of the priority queue ADT implemented as a pairing
// heap.
template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class PairingPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

public:
    // Each node within the pairing heap
    class Node {
        public:
            // TODO: After you add add one extra pointer (see below), be sure
            //       to initialize it here.
            explicit Node(const TYPE &val)
                : elt{ val }, child{ nullptr }, sibling{ nullptr }, parent{ nullptr }
            {}

            // Description: Allows access to the element at that Node's
            //              position. There are two versions, getElt() and a
            //              dereference operator, use whichever one seems
            //              more natural to you.
            // Runtime: O(1) - this has been provided for you.
            const TYPE &getElt() const { return elt; }
            const TYPE &operator*() const { return elt; }

            // The following line allows you to access any private data
            // members of this Node class from within the PairingPQ class.
            // (ie: myNode.elt is a legal statement in PairingPQ's add_node()
            // function).
            friend PairingPQ;

        private:
            TYPE elt;
            Node *child;
            Node *sibling;
            Node *parent;
            // TODO: Add one extra pointer (parent or previous) as desired.
    }; // Node


    // Description: Construct an empty pairing heap with an optional
    //              comparison functor.
    // Runtime: O(1)
    explicit PairingPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp }, root{NULL}, numNodes{0} {
        // TODO: Implement this function.
    } // PairingPQ()


    // Description: Construct a pairing heap out of an iterator range with an
    //              optional comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    template<typename InputIterator>
    PairingPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp }, root{NULL}, numNodes{0} {
        // TODO: Implement this function.
        for(InputIterator it = start; it != end; it++){
            push(*it);
        }

    } // PairingPQ()


    // Description: Copy constructor.
    // Runtime: O(n)
    PairingPQ(const PairingPQ &other) :
        BaseClass{ other.compare } {
        // TODO: Implement this function.
        // NOTE: The structure does not have to be identical to the original,
        //       but it must still be a valid pairing heap.

        Node* start = other.root;
        root = NULL;
        numNodes = 0;

        if(start == NULL){
            root = NULL;
            numNodes = 0;

        } else {

            std::deque<Node*> pqs;
            pqs.push_back(start);
            while(!pqs.empty()){
                Node* current = pqs.back();
                pqs.pop_back();
            
                if(current->child != NULL){
                    pqs.push_back(current->child);
                }

                if(current->sibling != NULL){
                    pqs.push_back(current->sibling);
                }

                if(current != NULL){
                    push(current -> elt);
                } else {
                    root = NULL;
                }
            }

        }

    } // PairingPQ()


    // Description: Copy assignment operator.
    // Runtime: O(n)
    PairingPQ &operator=(const PairingPQ &rhs) {
        // TODO: Implement this function.
        // HINT: Use the copy-swap method from the "Arrays and Containers"
        //       lecture.

        PairingPQ temp(rhs);
        std::swap(numNodes, temp.numNodes);
        std::swap(root, temp.root);

        return *this;
    } // operator=()


    // Description: Destructor
    // Runtime: O(n)
    ~PairingPQ() {
        // TODO: Implement this function.

        Node* start = root;
        std::deque<Node*> pqs;

        if(start != NULL){
            pqs.push_back(start);
            while(!pqs.empty()){
                Node* victim = pqs.back();
                Node* current = pqs.back();
                pqs.pop_back();
            
                if(current->child != NULL){
                    pqs.push_back(current->child);
                }

                if(current->sibling != NULL){
                    pqs.push_back(current->sibling);
                }

                delete victim;

            }
        }
    } // ~PairingPQ()


    // Description: Assumes that all elements inside the pairing heap are out
    //              of order and 'rebuilds' the pairing heap by fixing the
    //              pairing heap invariant. You CANNOT delete 'old' nodes
    //              and create new ones!
    // Runtime: O(n)
    virtual void updatePriorities() {
        // TODO: Implement this function.
        Node* start = root;
        std::deque<Node*> pqs;

        if(start != NULL){
            pqs.push_front(start);
            while(!pqs.empty()){
                Node* current = pqs.front();
                pqs.pop_front();
            
                if(current->child != NULL){
                    pqs.push_front(current->child);
                    current -> child = NULL;
                }

                if(current->sibling != NULL){
                    pqs.push_front(current->sibling);
                    current -> sibling = NULL;
                }

                current -> child = NULL;
                current -> sibling = NULL;
                current -> parent = NULL;
                //root->child = NULL;

                root = meld(root, current);
            }
        }

    } // updatePriorities()


    // Description: Add a new element to the pairing heap. This is already
    //              done. You should implement push functionality entirely in
    //              the addNode() function, and this function calls
    //              addNode().
    // Runtime: O(1)
    virtual void push(const TYPE &val) {
        addNode(val);
    } // push()


    // Description: Remove the most extreme (defined by 'compare') element
    //              from the pairing heap.
    // Note: We will not run tests on your code that would require it to pop
    //       an element when the pairing heap is empty. Though you are
    //       welcome to if you are familiar with them, you do not need to use
    //       exceptions in this project.
    // Runtime: Amortized O(log(n))
    virtual void pop() {
        // TODO: Implement this function.

        Node* victim = root;

        if(root->child == NULL){
            root = NULL;
            numNodes = 0;
            delete victim;

        } else {

            Node* check = root->child;

            //multipass

            std::deque<Node*> nodes;
            while(check != NULL){
                nodes.push_back(check);
                check = check->sibling;
            }

            while(nodes.size() > 1){
                Node* first = nodes.front();
                nodes.pop_front();
                Node* second = nodes.front();
                nodes.pop_front();

                first->sibling = NULL;
                first->parent = NULL;
                second->sibling = NULL;
                second->parent = NULL;

                nodes.push_back(meld(first,second));
            }



            root = nodes.front();
            numNodes -= 1;
            delete victim;

        }
    

    } // pop()


    // Description: Return the most extreme (defined by 'compare') element of
    //              the pairing heap. This should be a reference for speed.
    //              It MUST be const because we cannot allow it to be
    //              modified, as that might make it no longer be the most
    //              extreme element.
    // Runtime: O(1)
    virtual const TYPE &top() const {
        // TODO: Implement this function
        return root->elt;
    } // top()


    // Description: Get the number of elements in the pairing heap.
    // Runtime: O(1)
    virtual std::size_t size() const {
        return numNodes;
    } // size()

    // Description: Return true if the pairing heap is empty.
    // Runtime: O(1)
    virtual bool empty() const {
        // TODO: Implement this function
        return numNodes == 0; // TODO: Delete or change this line
    } // empty()


    // Description: Updates the priority of an element already in the pairing
    //              heap by replacing the element refered to by the Node with
    //              new_value. Must maintain pairing heap invariants.
    //
    // PRECONDITION: The new priority, given by 'new_value' must be more
    //               extreme (as defined by comp) than the old priority.
    //
    // Runtime: As discussed in reading material.
    void updateElt(Node* node, const TYPE &new_value) {
        // TODO: Implement this function
        node -> elt = new_value;

        //find leftmost
        Node* curr = node;
        Node* mom = node->parent;
        Node* bro = node->sibling;

        if(curr == mom->child){
            //leftmost
            mom -> child = bro;
        } else {
            //traverse
            Node* check = mom -> child;
            while(check->sibling != node){
                check = check->sibling;
            }
            check->sibling = bro;
        }

        node -> sibling = NULL;
        node -> parent = NULL;
        root = meld(root, node); 

    } // updateElt()


    // Description: Add a new element to the pairing heap. Returns a Node*
    //              corresponding to the newly added element.
    // NOTE: Whenever you create a node, and thus return a Node *, you must
    //       be sure to never move or copy/delete that node in the future,
    //       until it is eliminated by the user calling pop(). Remember this
    //       when you implement updateElt() and updatePriorities().
    // Runtime: O(1)
    Node* addNode(const TYPE &val) {
        // TODO: Implement this function

        Node* add = new Node(val);

        if(root == NULL){
            root = add;
            numNodes = 1;
        } else {
            root = meld(root, add);
            numNodes++;
        }

        return add; // TODO: Delete or change this line
    } // addNode()

 
private:
    // TODO: Add any additional member variables or member functions you
    //       require here.
    // TODO: We recommend creating a 'meld' function (see the Pairing Heap
    //       papers).

    Node* meld(Node *pa, Node *pb){

        if(pa == pb){
            return pa;
            
        } else if(this->compare(pa->elt,pb->elt)){

            Node* leftNode = pb->child;

            pb -> child = pa;
            pa -> parent = pb;
            pa -> sibling = leftNode;

            return pb;

        } else {
            
            Node* leftNode = pa->child;

            pa -> child = pb;
            pb -> parent = pa;
            pb -> sibling = leftNode;

            return pa;
            
        }
    }

    Node *root;
    size_t numNodes;




    // NOTE: For member variables, you are only allowed to add a "root
    //       pointer" and a "count" of the number of nodes. Anything else
    //       (such as a deque) should be declared inside of member functions
    //       as needed.
};


#endif // PAIRINGPQ_H
