clear
make part1 && ./part1 1000 shortbooks.txt

sort -nk 2,2 -s shortbooks.txt | head -20
