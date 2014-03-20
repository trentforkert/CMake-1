// Output format detection: Only needed for ELF, so non-ELF should
// result in an empty string. Current detection is very likely wrong.
version(Windows)
  enum ABI = "";
else version(OSX)
  enum ABI = "";
else version(ARM)
  enum ABI = "ELF ARM"; // TODO: ELF EABI
else                    // TODO: MIPS
  enum ABI = "ELF";

// cast to an int to get rid of any U or LU suffix
enum int SIZEOF_DATA_PTR = (void*).sizeof;

enum BUF_SIZE = 64; // oversized to prevent bounds problems

enum char[BUF_SIZE] info_abi = "INFO:abi[" ~ ABI ~ "]";
enum char[BUF_SIZE] info_dptr = "INFO:sizeof_dptr[" ~ SIZEOF_DATA_PTR.stringof ~ "]";

int main(string[] args)
{
  int require = 0;
  require += info_abi[args.length];
  require += info_dptr[args.length];
  return require;
}
