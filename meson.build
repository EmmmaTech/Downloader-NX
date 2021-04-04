project('Downloader', ['c', 'cpp'],
    version: '1.0.0',
    default_options: [ 'buildtype=release', 'strip=true', 'b_ndebug=if-release', 'cpp_std=c++1z' ],
)

subdir('lib/borealis/library')

c = run_command('./scripts/source-wildcard.sh')
files = c.stdout().strip().split('\n')

borealis_demo = executable(
    'Downloader',
    [ files, borealis_files ],
    dependencies : borealis_dependencies,
    install: true,
    include_directories: [ borealis_include, include_directories('include')],
    cpp_args: [ '-g', '-O2', '-DBRLS_RESOURCES="./resources/"', ] + borealis_cpp_args
)