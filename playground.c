struct AVLnode * _AVLnodeAdd (struct AVLnode* current, TYPEnewValue) {
   struct AVLnode * newnode;
   if (current == 0) {        // You have found NULL node, insert
      newnode = (struct AVLnode *) malloc(sizeof(struct AVLnode));
      assert(newnode != 0);
      newnode->value = newValue;newnode->left =
      newnode->right = 0;return newnode;//why don’t we balance here ??
   
   }
   // Less than, go left
   else if (LT(newValue, current->value)) {
      current->left = AVLnodeAdd(current->left, newValue);
   }
   // Greater than, go right
   else {
      current->right = AVLnodeAdd(current->right, newValue);
   }
   return balance(current);    /* <-NEW  the call on balance */
}
