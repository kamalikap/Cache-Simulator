#!/bin/sh
#This is a comment!
echo "\n Filename: - gcc-10K.memtrace Direct Mapped\n"
./cachesim gcc-10K.memtrace 524288 16 1
echo "\n Filename: - gcc-10K.memtrace 2-way set associative\n"
./cachesim gcc-10K.memtrace 524288 16 2
echo "\n Filename: - gcc-10K.memtrace 4-way set associative\n"
./cachesim gcc-10K.memtrace 524288 16 4
echo "\n Filename: - gcc-1M.memtrace Direct Mapped\n"
./cachesim gcc-1M.memtrace 524288 16 1
echo "\n Filename: - gcc-1M.memtrace 2-way set associative\n"
./cachesim gcc-1M.memtrace 524288 16 2
echo "\n Filename: - gcc-1M.memtrace 4-way set associative\n"
./cachesim gcc-1M.memtrace 524288 16 4
echo "\n Filename: - gcc-1M.memtrace Direct mapped 4- victim cache\n"
./cachesim gcc-1M.memtrace 524288 16 1 4
echo "\n Filename: - gcc-1M.memtrace Direct mapped 8- victim cache\n"
./cachesim gcc-1M.memtrace 524288 16 1 8
echo "\n Filename: - gcc-1M.memtrace Direct mapped 16- victim cache\n"
./cachesim gcc-1M.memtrace 524288 16 1 16
echo "\n Filename: - gcc-1M.memtrace 4-way set associative 4- victim cache\n"
./cachesim gcc-1M.memtrace 524288 16 4 4
echo "\n Filename: - gcc-1M.memtrace 4-way set associative 8- victim cache\n"
./cachesim gcc-1M.memtrace 524288 16 4 8
echo "\n Filename: - gcc-1M.memtrace 4-way set associative 16- victim cache\n"
./cachesim gcc-1M.memtrace 524288 16 4 16
echo "\n Filename: - gcc-10K.memtrace Fully Associative\n"
./cachesim gcc-10K.memtrace 524288 16 0
echo "\n Filename: - gcc-1M.memtrace Fully Associative\n"
./cachesim gcc-1M.memtrace 524288 16 0
echo "\n Filename: - gcc-1M.memtrace Fully Associative 4- victim cache\n"
./cachesim gcc-1M.memtrace 524288 16 0 4
echo "\n Filename: - gcc-1M.memtrace Fully Associative 8- victim cache\n"
./cachesim gcc-1M.memtrace 524288 16 0 8
echo "\n Filename: - gcc-1M.memtrace Fully Associative 16- victim cache\n"
./cachesim gcc-1M.memtrace 524288 16 0 16


