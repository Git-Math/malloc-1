#!/bin/bash -x

TIME_FLAG=$(test "$(uname -s)" == Linux && echo v || echo l)

export DYLD_LIBRARY_PATH=.
export DYLD_INSERT_LIBRARIES="libft_malloc.so"
export DYLD_FORCE_FLAT_NAMESPACE=1

nm libft_malloc.so | grep -E 'free|alloc'

test -d test || tar -xvf test.tar.gz

for i in 0 1 2 3 3_bis 4 5 6 7; do
    clang -Wall -Wextra -Iinc -o "test$i" "test/test$i.c" -rpath . -L. -lft_malloc \
        && clang -o "ctrl$i" "test/test$i.c" -D CTRL \
        && diff -y \
                <(/usr/bin/time "-$TIME_FLAG" "./test$i" 2>&1) \
                <(/usr/bin/time "-$TIME_FLAG" "./ctrl$i" 2>&1)
done

exit 0 # eheh
