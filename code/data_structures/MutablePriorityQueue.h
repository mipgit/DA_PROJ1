/** @file MutablePriorityQueue.h
 *  @brief Contains the definition of the MutablePriorityQueue class.
 *
 *  The code is adapted from DA 24/25
 * 
 *  This file defines the template class `MutablePriorityQueue`, which is a data structure 
 *  that maintains a priority queue with mutable keys. The class provides methods for 
 *  inserting, extracting the minimum element, and decreasing the key of an element 
 *  in the priority queue. The class assumes that the elements have a field `queueIndex` 
 *  that tracks their position in the heap, and that elements support the `<` operator for comparison.
 */

 #ifndef DA_TP_CLASSES_MUTABLEPRIORITYQUEUE
 #define DA_TP_CLASSES_MUTABLEPRIORITYQUEUE
 
 #include <vector>
 
 /**
  * class T must have: (i) accessible field int queueIndex; (ii) operator< defined.
  */
 
 /**
  * @class MutablePriorityQueue
  * @brief A priority queue with mutable keys.
  *
  * The `MutablePriorityQueue` class implements a min-heap based priority queue where each 
  * element can have its key decreased after insertion. The class provides efficient operations 
  * for extracting the minimum element, inserting elements, and decreasing the key of an element.
  * Elements in the queue must have a member `queueIndex` and must implement the `<` operator 
  * for comparison.
  *
  * @tparam T The type of elements stored in the priority queue. The class assumes that the type 
  * must support the `<` operator for comparison and must have an accessible field `queueIndex`.
  */
 template <class T>
 class MutablePriorityQueue { 
     std::vector<T *> H; ///< The underlying vector storing the heap elements.

     /**
     * @brief Ensures the heap property is maintained when moving an element up the heap.
     * 
     * This method is called after an insertion or a decrease-key operation. It moves an element 
     * up the heap to restore the heap property.
     *
     * @param i The index of the element to move up.
     */
     void heapifyUp(unsigned i);

     /**
     * @brief Ensures the heap property is maintained when moving an element down the heap.
     * 
     * This method is called after extracting the minimum element. It moves an element down the heap 
     * to restore the heap property.
     *
     * @param i The index of the element to move down.
     */
     void heapifyDown(unsigned i);


     /**
     * @brief Sets the value of an element at a given index and updates its `queueIndex`.
     * 
     * @param i The index where the element should be set.
     * @param x The element to set at index `i`.
     */
     inline void set(unsigned i, T * x);

 public:
    /**
     * @brief Default constructor for the MutablePriorityQueue class.
     *
     * Initializes an empty priority queue. The underlying vector `H` starts with one dummy element 
     * at index 0 to make the heap operations easier (1-based indexing).
     */ 
     MutablePriorityQueue();

     /**
     * @brief Inserts an element into the priority queue.
     * 
     * This method adds the element to the heap and ensures that the heap property is maintained by
     * calling `heapifyUp`.
     *
     * @param x A pointer to the element to be inserted.
     */
     void insert(T * x);

     /**
     * @brief Extracts the minimum element from the priority queue.
     * 
     * This method removes and returns the element with the smallest value from the priority queue,
     * and then restores the heap property by calling `heapifyDown`.
     *
     * @return A pointer to the minimum element in the queue.
     */
     T * extractMin();

     /**
     * @brief Decreases the key of an element in the priority queue.
     * 
     * This method is used to decrease the value of an element. It ensures that the heap property is 
     * maintained by calling `heapifyUp` after the key decrease.
     *
     * @param x A pointer to the element whose key should be decreased.
     */
     void decreaseKey(T * x);

     /**
     * @brief Checks whether the priority queue is empty.
     *
     * This method returns true if the priority queue contains no elements.
     *
     * @return `true` if the queue is empty, otherwise `false`.
     */
     bool empty();
 };
 
 // Index calculations
 #define parent(i) ((i) / 2)   ///< The index of the parent of the element at index `i`.
 #define leftChild(i) ((i) * 2) ///< The index of the left child of the element at index `i`.

 
 template <class T>
 MutablePriorityQueue<T>::MutablePriorityQueue() {
     H.push_back(nullptr);
     // indices will be used starting in 1
     // to facilitate parent/child calculations
 }
 
 template <class T>
 bool MutablePriorityQueue<T>::empty() {
     return H.size() == 1;
 }
 
 template <class T>
 T* MutablePriorityQueue<T>::extractMin() {
     auto x = H[1];
     H[1] = H.back();
     H.pop_back();
     if(H.size() > 1) heapifyDown(1);
     x->queueIndex = 0;
     return x;
 }
 
 template <class T>
 void MutablePriorityQueue<T>::insert(T *x) {
     H.push_back(x);
     heapifyUp(H.size()-1);
 }
 
 template <class T>
 void MutablePriorityQueue<T>::decreaseKey(T *x) {
     heapifyUp(x->queueIndex);
 }
 
 template <class T>
 void MutablePriorityQueue<T>::heapifyUp(unsigned i) {
     auto x = H[i];
     while (i > 1 && *x < *H[parent(i)]) {
         set(i, H[parent(i)]);
         i = parent(i);
     }
     set(i, x);
 }
 
 template <class T>
 void MutablePriorityQueue<T>::heapifyDown(unsigned i) {
     auto x = H[i];
     while (true) {
         unsigned k = leftChild(i);
         if (k >= H.size())
             break;
         if (k+1 < H.size() && *H[k+1] < *H[k])
             ++k; // right child of i
         if ( ! (*H[k] < *x) )
             break;
         set(i, H[k]);
         i = k;
     }
     set(i, x);
 }
 
 template <class T>
 void MutablePriorityQueue<T>::set(unsigned i, T * x) {
     H[i] = x;
     x->queueIndex = i;
 }
 
 #endif /* DA_TP_CLASSES_MUTABLEPRIORITYQUEUE */