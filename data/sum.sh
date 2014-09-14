#!/bin/bash

paste <(sort $1 |cut -f-2) <(sort $2 | cut -f-2) | awk '{ print $1 "\t" $2 "\t" $3 "\t" $4  "\t" ($2+$4)}' | sort -nk5
