#!/bin/bash -x

TIME_FLAG=$(test "$(uname -s)" == Linux && echo v || echo l)

nm libft_malloc.so | grep -E 'free|alloc'

test -d test || tar -xvf test.tar.gz

for i in 0 1 2 3 3_bis 4 5 6 7; do
    clang -Wall -Wextra -Iinc -o "test$i" "test/test$i.c"  -L. -lft_malloc \
        && clang -o "ctrl$i" "test/test$i.c" -D CTRL \
        && diff -y \
                <(./run.sh /usr/bin/time "-$TIME_FLAG" "./test$i" 2>&1) \
                <(/usr/bin/time "-$TIME_FLAG" "./ctrl$i" 2>&1)
done

PAGE_TEST0="$(./run.sh /usr/bin/time -l ./test0 2>&1 | grep 'page rec' | cut -dp -f1)"
PAGE_TEST1="$(./run.sh /usr/bin/time -l ./test1 2>&1 | grep 'page rec' | cut -dp -f1)"
echo "$PAGE_TEST1 - $PAGE_TEST0" | bc

exit 0 # eheh
