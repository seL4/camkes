#!/bin/bash
# @TAG(NICTA_BSD)

# Generate XBM representations of the characters from the font Nimbus Mono
# Regular.

echo '#include <stdlib.h>'>chars.c
for i in a b c d e f g h i j k l m n o p q r s t u v w x y z A B C D E F G H I J K L M N O P Q R S T U V W X Y Z; do
    convert -resize 14x26\! -font Nimbus-Mono-Regular -pointsize 26 label:$i $i.xbm
    cat $i.xbm >>chars.c
    rm $i.xbm
done
for i in 1 2 3 4 5 6 7 8 9 0; do
    convert -resize 14x26\! -font Nimbus-Mono-Regular -pointsize 26 label:$i digit$i.xbm
    cat digit$i.xbm >>chars.c
    rm digit$i.xbm
done

cat - >>chars.c <<EOT
char *to_pixels(char c) {
    static char space_bits[sizeof(Z_bits)] = { 0 };
    switch(c) {
        case ' ':
            return space_bits;
EOT

for i in a b c d e f g h i j k l m n o p q r s t u v w x y z A B C D E F G H I J K L M N O P Q R S T U V W X Y Z; do
    cat - >>chars.c <<EOT
case '$i':
    return ${i}_bits;
EOT
done
for i in 1 2 3 4 5 6 7 8 9 0; do
    cat - >>chars.c <<EOT
case '$i':
    return digit${i}_bits;
EOT
done
cat - >>chars.c <<EOT
default:
    return NULL;
    }
}
EOT
