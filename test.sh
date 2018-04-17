#!/bin/bash -x

TIME_FLAG=$(test "$(uname -s)" == Linux && echo v || echo l)

export DYLD_LIBRARY_PATH=.
export DYLD_INSERT_LIBRARIES="libft_malloc.so"
export DYLD_FORCE_FLAT_NAMESPACE=1

nm libft_malloc.so | grep -E 'free|alloc'

for i in 0 1 2 3 3_bis 4 5; do
    clang -Wall -Wextra -Iinc -o "test$i" "test/test$i.c" -rpath . -L. -lft_malloc \
        && /usr/bin/time "-$TIME_FLAG" "./test$i"
done
