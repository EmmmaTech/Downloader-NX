project('Downloader', ['c', 'cpp'],
    version: '1.0.0',
    default_options: [ 'buildtype=release', 'strip=true', 'b_ndebug=if-release', 'cpp_std=c++1z' ],
)

curl = dependency('curl')

subdir('lib/borealis/library')

c = run_command('./scripts/source-wildcard.sh')
files = c.stdout().strip().split('\n')

Downloader = executable(
    'Downloader',
    [ files, borealis_files ],
    dependencies : [borealis_dependencies, curl],
    install: true,
    include_directories: [ borealis_include, include_directories('include'), include_directories('lib/borealis/library/include/borealis/extern/nlohmann')],
    cpp_args: [ '-g', '-O2', '-DBRLS_RESOURCES="./resources/"', '-D_DOWNLOADER_PC' ] + borealis_cpp_args
)