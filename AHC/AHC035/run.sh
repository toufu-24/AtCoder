#!/usr/sbin/zsh

# compile
g++ -std=c++20 -O2 sort_sum_strongest.cpp -o a.out

cd tools
cargo run -r --bin tester ../a.out < in/0000.txt > ../out.txt 
# for i in {0..9}
# do
#     cargo run -r --bin tester ../a.out < in/000$i.txt > ../out.txt 
# done
cd ..
