#!/bin/bash

paste <(sort $1 | grep ^[0246] | cut -f1,2) <(sort $1 | grep ^[1357] | cut -f1,2) | awk '{ print $1 "\t" $2 "\t" $3 "\t" $4  "\t" ($2+$4)}' | sort -nk5
