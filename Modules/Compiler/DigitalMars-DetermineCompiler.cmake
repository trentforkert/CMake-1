
set(_compiler_id_pp_test "defined(__DMC__)")

set(_compiler_id_version_compute "
# define @PREFIX@COMPILER_VERSION_MAJOR @MACRO_HEX@(__DMC__ >> 8)
# define @PREFIX@COMPILER_VERSION_MINOR @MACRO_HEX@(__DMC__ & 0xFF)")
