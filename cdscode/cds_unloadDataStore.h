//This is the global variable defined in globals.c and to be
//used by various files.
extern struct colDataStore cdsInfo;


/*
  The function opens the ndx files in wb mode and persists the stack and bst to
  the primaryindex and hashtable to the secondary index. This function closes every
  file pointer that is open.

  In short this function populates the different structures and the cdsInfo variable.
  return 0 on success and 1 on failure to unload and 2 if a datastore is already closed.


*/
int cds_unloadDataStore();