#include <mppa/osconfig.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <mppa_dl_lib.h>

extern const char plt_test_mdo[];

// this function should be used by the dynamic module
int self_contained_magic_func_increment_used_for_reloc(int arg){
  return arg + 1;
}

int main(int argc, char *argv[])
{
  mppa_dl_handle_t *handle;
  int status = 0;
  void *f_ptr;

  handle = mppa_dl_handle_new(mppa_dl_this(), 0);
  if (handle == NULL) {
    fprintf(stderr, "mppa_dl_handle_new failed\n");
    status = -1;
    goto fail;
  }
    
  if (mppa_dl_load_buffer(handle, plt_test_mdo) == -1) {
    fprintf(stderr, "mppa_dl_load_buffer failed: %s\n", mppa_dl_errstr(handle));
    status = -1;
    goto fail;
  }
  
  if ((f_ptr = mppa_dl_sym(handle, "mppa_dl_main")) == NULL) {
    fprintf(stderr, "No mppa_dl_main found in plt_test module\n");
    goto fail;
  } else {
    printf("Found mppa_dl_main in plt_test module at {{%p}}\n",  f_ptr);
    printf("Module load address is {{%p}}\n", mppa_dl_load_addr(handle));

    status = ((int (*)(int, char **))f_ptr)(argc, argv);
  }

  printf("Returned status: %d\n", status);

 fail:
  return status;
}