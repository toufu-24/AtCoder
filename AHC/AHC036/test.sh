g++ -std=c++20 -O2 $1 -o a.out
echo "Compiled"
cd tools
sum=0
for i in {0..99}; do
    input=in/$(printf "%04d" $i).txt
    ../a.out < $input > out/$(printf "%04d" $i).txt
    res=$(cargo run -r --bin tester $input out/$(printf "%04d" $i).txt)
    sum=$((sum+res))
done
echo "Sum: "
echo $sum
echo "Average: "
echo $(($sum/100))