{
  'targets': [
    {
      'target_name': 'ccfits-native',
      'sources': [ 'src/ccfits.cc', 'src/fits.cc', 'src/hdu.cc' ],
      'include_dirs': ["<!@(node -p \"require('node-addon-api').include\")", "/usr/include/CCfits"],
      'dependencies': ["<!(node -p \"require('node-addon-api').gyp\")"],
      'cflags_cc': [ '-fexceptions', '-frtti', '-std=c++17' ],
      'libraries': [
        '-lCCfits',
        '-lcfitsio',
      ],
      'xcode_settings': {
        'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
        'CLANG_CXX_LIBRARY': 'libc++',
        'MACOSX_DEPLOYMENT_TARGET': '10.7'
      },
      'msvs_settings': {
        'VCCLCompilerTool': { 'ExceptionHandling': 1 },
      }
    }
  ]
}
