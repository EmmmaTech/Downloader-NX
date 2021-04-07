project('Downloader', ['c', 'cpp'],
    version: '1.0.0',
    default_options: [ 'buildtype=release', 'strip=true', 'b_ndebug=if-release', 'cpp_std=c++1z', 'c_std=c17' ],
)

curl = dependency('curl')
zlib = dependency('zlib')

subdir('lib/borealis/library')

c = run_command('./scripts/source-wildcard.sh')
files = c.stdout().strip().split('\n')

lib_includes = include_directories(
    'lib/borealis/library/include/borealis/extern/nlohmann',
)

Downloader = executable(
    'Downloader',
    [ files, borealis_files ],
    dependencies : [borealis_dependencies, curl, zlib],
    install: true,
    include_directories: [ borealis_include, include_directories('include'), lib_includes],
    cpp_args: [ '-g', '-O2', '-DBRLS_RESOURCES="./resources/"', '-D_DOWNLOADER_PC', ] + borealis_cpp_args
)