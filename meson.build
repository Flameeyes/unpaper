# SPDX-FileCopyrightText: 2020 The unpaper authors
#
# SPDX-License-Identifier: MIT

project('unpaper', 'c', version : '7.0.0', default_options : ['c_std=c11'])

if not meson.version().version_compare('>0.57')
    error('Meson 0.57 or later required')
endif

pymod = import('python')

add_global_arguments('-D_POSIX_C_SOURCE=200809L', language : 'c')

cc = meson.get_compiler('c')

if not cc.has_function('strdup', prefix : '#include <string.h>', args : ['-D_POSIX_C_SOURCE=200809L'])
    error('A C library compatible with POSIX.1-2008 is required.')
endif

if cc.has_argument('-Werror=int-conversion')
    add_project_arguments('-Werror=int-conversion', language : 'c')
endif

unpaper_deps = [
    dependency('libavformat'), dependency('libavcodec'), dependency('libavutil'),
    dependency('libprotobuf-c', version: '>= 1.0.0'),
    cc.find_library('m', required : false)
]

conf_data = configuration_data()
conf_data.set('version', meson.project_version())
configure_file(input: 'version.h.in', output: 'version.h', configuration: conf_data)

protoc_c = find_program('protoc-c', required: true)

protoc_c_generator = generator(
    protoc_c,
    output: ['@BASENAME@.pb-c.c', '@BASENAME@.pb-c.h'],
    arguments: ['--proto_path=@CURRENT_SOURCE_DIR@', '--c_out=@BUILD_DIR@', '@INPUT@']
)

proto_c_parser = protoc_c_generator.process(
    'api/unpaper.proto',
    preserve_path_from: meson.current_source_dir()
)

protoc = find_program('protoc', required: true)

proto_py_parser = custom_target(
    'proto_py_parser',
    command: [protoc, '--proto_path=@CURRENT_SOURCE_DIR@', '--python_out',  '@OUTDIR@', '@INPUT@'],
    input: ['api/unpaper.proto'],
    output: ['unpaper_pb2.py']
)

proto_python = pymod.find_installation(required: true, modules: ['google.protobuf', 'click'])

default_jp_header = custom_target(
    'default_jp_header',
    command: [proto_python, '@CURRENT_SOURCE_DIR@/api/compile_job_parameters.py', '@INPUT@', '@OUTPUT@'],
    env: {
        'PYTHONPATH': meson.current_build_dir() + '/api'
    },
    input: ['api/default-job-parameters.textpb'],
    output: ['default-job-parameters.h'],
    depends: proto_py_parser
)

unpaper = executable(
    'unpaper',
    'file.c', 'imageprocess.c', 'parse.c', 'tools.c', 'unpaper.c',
    proto_c_parser, default_jp_header,
    dependencies : unpaper_deps,
    install : true,
)

sphinx = find_program('sphinx-build', required: true, version: '>= 3.4')

custom_target(
    'man',
    command: [sphinx, '-b', 'man', join_paths(meson.source_root(), 'doc'), '@OUTDIR@'],
    input: ['doc/conf.py', 'doc/index.rst', 'doc/unpaper.1.rst'],
    output: 'unpaper.1',
    install: true,
    install_dir: join_paths(get_option('prefix'), get_option('mandir'), 'man1'),
)

python = pymod.find_installation(required: false, modules: ['pytest', 'PIL'], disabler: true)

if not python.found()
    warning('pytest or Pillow not found, tests will not be performed.')
endif

test(
    'pytest suite',
    python,
    args: [
        '-m', 'pytest', meson.project_source_root() + '/tests/unpaper_tests.py'
    ],
    env: [
        'TEST_IMGSRC_DIR=' + meson.project_source_root() + '/tests/source_images/',
        'TEST_GOLDEN_DIR=' + meson.project_source_root() + '/tests/golden_images/',
        'TEST_UNPAPER_BINARY=' + unpaper.full_path(),
    ],
    timeout : -1,
)
