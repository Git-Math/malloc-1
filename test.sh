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

exit 0 # eheh
