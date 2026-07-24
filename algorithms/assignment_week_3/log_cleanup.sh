#!/bin/bash

LOG_FILE="blob/server_access.log"

sed -i -E \
    -e '/^#/d' \
    -e 's|HTTP/1\.0|HTTP/1.1|g' \
    -e 's/[0-9]{4}[-?]?[0-9]{4}[-?]?[0-9]{4}[-?]?[0-9]{4}/XXXX-XXXX-XXXX-XXXX/g' \
    $LOG_FILE
