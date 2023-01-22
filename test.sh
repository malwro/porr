#!/bin/bash

avg_time() {
    #
    # usage: avg_time n command ...
    #
    n=$1; shift
    (($# > 0)) || return                   # bail if no command given
    for ((i = 0; i < n; i++)); do
        { time -p "$@" &>/dev/null; } 2>&1 # ignore the output of the command
                                           # but collect time's output in stdout
    done | awk '
        /real/ { real = real + $2; nr++ }
        /user/ { user = user + $2; nu++ }
        /sys/  { sys  = sys  + $2; ns++}
        END    {
                 if (nr>0) printf("real %f\n", real/nr);
                 if (nu>0) printf("user %f\n", user/nu);
                 if (ns>0) printf("sys %f\n",  sys/ns)
               }'
}


# case "$1" in
#     "") ;;
#     avg_time) "$@"; exit;;
#     *) echo "error"
# esac


g++ -o sequential/seq sequential/seq.hpp sequential/seq.cpp sequential/main.cpp

g++ -o parallel/par parallel/par.hpp parallel/par.cpp parallel/main.cpp -fopenmp


echo "SEQUENTIAL"
echo "SHORT"
avg_time 10 sequential/seq files/10_multiplied_text.txt 
echo "MEDIUM"
avg_time 10 sequential/seq files/50_multiplied_text.txt 
echo "LONG"
avg_time 10 sequential/seq files/150_multiplied_text.txt 
echo "---------------------------------------------------"

echo "PARALLEL"
echo "2 THREADS"
echo "SHORT"
avg_time 10 parallel/par files/10_multiplied_text.txt 2
echo "MEDIUM"
avg_time 10 parallel/par files/50_multiplied_text.txt 2
echo "LONG"
avg_time 10 parallel/par files/150_multiplied_text.txt 2
echo "---------------------------------------------------"

echo "4 THREADS"
echo "SHORT"
avg_time 10 parallel/par files/10_multiplied_text.txt 4
echo "MEDIUM"
avg_time 10 parallel/par files/50_multiplied_text.txt 4
echo "LONG"
avg_time 10 parallel/par files/150_multiplied_text.txt 4
echo "---------------------------------------------------"

echo "6 THREADS"
echo "SHORT"
avg_time 10 parallel/par files/10_multiplied_text.txt 6
echo "MEDIUM"
avg_time 10 parallel/par files/50_multiplied_text.txt 6
echo "LONG"
avg_time 10 parallel/par files/150_multiplied_text.txt 6
echo "---------------------------------------------------"

echo "8 THREADS"
echo "SHORT"
avg_time 10 parallel/par files/10_multiplied_text.txt 8
echo "MEDIUM"
avg_time 10 parallel/par files/50_multiplied_text.txt 8
echo "LONG"
avg_time 10 parallel/par files/150_multiplied_text.txt 8
echo "---------------------------------------------------"

echo "10 THREADS"
echo "SHORT"
avg_time 10 parallel/par files/10_multiplied_text.txt 10
echo "MEDIUM"
avg_time 10 parallel/par files/50_multiplied_text.txt 10
echo "LONG"
avg_time 10 parallel/par files/150_multiplied_text.txt 10
echo "---------------------------------------------------"

echo "12 THREADS"
echo "SHORT"
avg_time 10 parallel/par files/10_multiplied_text.txt 12
echo "MEDIUM"
avg_time 10 parallel/par files/50_multiplied_text.txt 12
echo "LONG"
avg_time 10 parallel/par files/150_multiplied_text.txt 12
echo "---------------------------------------------------"

echo "14 THREADS"
echo "SHORT"
avg_time 10 parallel/par files/10_multiplied_text.txt 14
echo "MEDIUM"
avg_time 10 parallel/par files/50_multiplied_text.txt 14
echo "LONG"
avg_time 10 parallel/par files/150_multiplied_text.txt 14
