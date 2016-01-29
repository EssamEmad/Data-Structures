# Generic-C-libraries
##Vector And Hashset
Generic C Vector and Generic C HashSet that can be used in any project. They are implemented using void pointers to support any type. The starter project was downloaded from Stanford's cs107 course (Assignment 3).
##SpaseStringArray
The sparse string array, is a data structure that works on char * type. It is composed of a number of groups (specified by the client) each group stores a bitmap of boolean, where the indeces containing true, correspond to strings stored. Otherwise they are empty strings.
The sparse string array is typically used when memorry is the most important aspect. It is slower than the c-array or the vector library we created. But, on the other hand it is so efficient with memory usage. (The sparse string array hasn't been tested)
##Usage
Download the c and header files.
##TODO:
- [ ] Write a make file.
- [ ] Optimize the sparsestring array to use 1 bit types instead of 4 byte booleans.
