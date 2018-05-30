#!/bin/sh

api_key=$1

valgrind --tool=callgrind\
  --instr-atstart=no\
  --callgrind-out-file=callgrind.stockspan\
  ./1.2-stock-span GOOGL $api_key;

callgrind_annotate --auto=yes --inclusive=yes callgrind.stockspan.1 2>/dev/null\
  | grep -E 'stock_span_stack \(1x\)';
callgrind_annotate --auto=yes --inclusive=yes callgrind.stockspan.2 2>/dev/null\
  | grep -E 'stock_span_simple \(1x\)';
