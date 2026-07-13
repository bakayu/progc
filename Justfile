# Clean up the build directory
clean:
    rm -rf build/

# Build a specific C file and output to build/
build file:
    @mkdir -p build
    gcc "{{file}}" -o "build/$(basename "{{file}}" .c)"

# Build and run a specific C file, forwarding any extra flags or arguments
run file *args:
    @mkdir -p build
    gcc "{{file}}" -o "build/$(basename "{{file}}" .c)"
    ./build/$(basename "{{file}}" .c) {{args}}
