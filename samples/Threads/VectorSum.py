# -*- coding: utf-8 -*-
import threading

def get_data(data_size):
    """ (NoneType) -> list of int
    """
    return [1]*data_size;

def sum_data(data, start, finish):
    """ (list of int, int, int) -> int
    """
    return sum(data[start:finish])

def thread_proc(data, start, finish, result_list, result_index):
    result = sum_data(data, start, finish)
    result_list[result_index] = result

if __name__ == "__main__":
    num_threads = 8
    data_size = 1000013
    threads = []
    thread_params = []
    thread_results = [0]*num_threads
    data = get_data(data_size)
    chunk_size = data_size // num_threads
    index = 0
    prev = 0
    #print(chunk_size)
    for i in range(0,num_threads):
        if i == num_threads - 1:
            index = data_size
        else:
            index += chunk_size
        #print(index)
        
        thread_params.append((data, prev, index, thread_results, i))
        prev = index
        
        if i < num_threads - 1:
            thread = threading.Thread(target = thread_proc, args=thread_params[i])
            threads.append(thread)
            thread.start()
    
    main_thread_params = thread_params[num_threads - 1]
    thread_proc(*main_thread_params)        
    for i in range(0, num_threads - 1):
        threads[i].join()
        
    result_sum = 0
    for i in range(0,num_threads):
        result_sum += thread_results[i]

       
            
    print("Result:{0:>8}".format(result_sum))
    