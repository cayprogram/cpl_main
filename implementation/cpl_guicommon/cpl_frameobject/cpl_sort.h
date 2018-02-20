#ifndef CPL_SORT_H
#define CPL_SORT_H

class cpl_Sort {

public:
	/** quick sort [growth order]*/
    static void QuickSort(float array[], int index_array[], int num_entry);

	/** quick sort [growth order]*/
    static void QuickSort(int   array[], int index_array[], int num_entry);

    /** Filter Array according to basic index array.*/
    static void FilterArray(float array[], int index_array[], int num_entry, int descend);

    /** Filter Array according to basic index array. */
    static void FilterArray(int array[], int index_array[], int num_entry, int descend);

    /** Reverse Array according.*/
    static void ReverseArray(int array[], int num_entry);
};

#endif //CPL_SORT_H
