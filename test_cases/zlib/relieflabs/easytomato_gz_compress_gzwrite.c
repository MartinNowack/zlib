#include "zlib.h"
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <zlib.h>

#define BUFLEN 1024

int main(argc, argv)
    int argc;
    char *argv[];
{
    printf("=== DEBUG: Test execution started ===\n");
    printf("DEBUG: argc=%d\n", argc);
    
    /* Sequence: gzwrite,gzerror */
    gzFile out = NULL;
    char buf[BUFLEN];
    int len = 0;
    int err = 0;
    int ret = 0;
    
    printf("DEBUG: Variables initialized - out=%p, len=%d, err=%d, ret=%d\n", 
           (void*)out, len, err, ret);
    
    printf("DEBUG: Calling memset to clear buffer...\n");
    memset(buf, 0, BUFLEN);
    printf("DEBUG: memset completed, buffer cleared\n");
    
    printf("Opening gzip file for writing...\n");
    /* Open a gzip file for writing */
    printf("DEBUG: About to call gzopen with filename='test_output.gz', mode='wb'\n");
    out = gzopen("test_output.gz", "wb");
    printf("DEBUG: gzopen returned, out=%p\n", (void*)out);
    
    if (out == NULL) {
        printf("DEBUG: Condition check - out == NULL is TRUE\n");
        fprintf(stderr, "failed to open output file\n");
        printf("DEBUG: Returning -1 due to gzopen failure\n");
        return -1;
    }
    printf("DEBUG: Condition check - out == NULL is FALSE\n");
    printf("Successfully opened test_output.gz\n");
    
    /* Prepare some test data */
    printf("DEBUG: About to call strcpy to prepare test data...\n");
    strcpy(buf, "This is test data for gzwrite");
    printf("DEBUG: strcpy completed\n");
    
    printf("DEBUG: About to call strlen...\n");
    len = strlen(buf);
    printf("DEBUG: strlen returned %d\n", len);
    printf("Prepared test data: '%s' (length: %d)\n", buf, len);
    
    /* Write data using gzwrite */
    printf("Calling gzwrite with %d bytes...\n", len);
    printf("DEBUG: About to call gzwrite(out=%p, buf=%p, len=%u)\n", 
           (void*)out, (void*)buf, (unsigned)len);
    ret = gzwrite(out, buf, (unsigned)len);
    printf("DEBUG: gzwrite returned\n");
    printf("gzwrite executed with return value: %d\n", ret);
    
    printf("DEBUG: Checking if ret == 0...\n");
    if (ret == 0) {
        printf("DEBUG: Condition check - ret == 0 is TRUE\n");
        printf("DEBUG: About to call gzerror...\n");
        const char *error_msg = gzerror(out, &err);
        printf("DEBUG: gzerror returned, error_msg='%s', err=%d\n", 
               error_msg ? error_msg : "NULL", err);
        fprintf(stderr, "gzwrite failed: %s (error code: %d)\n", error_msg, err);
        printf("DEBUG: About to call gzclose due to write failure...\n");
        gzclose(out);
        printf("DEBUG: gzclose completed, returning -1\n");
        return -1;
    }
    printf("DEBUG: Condition check - ret == 0 is FALSE\n");
    
    printf("DEBUG: Checking if ret != len (ret=%d, len=%d)...\n", ret, len);
    if (ret != len) {
        printf("DEBUG: Condition check - ret != len is TRUE\n");
        printf("DEBUG: About to call gzerror...\n");
        const char *error_msg = gzerror(out, &err);
        printf("DEBUG: gzerror returned, error_msg='%s', err=%d\n", 
               error_msg ? error_msg : "NULL", err);
        fprintf(stderr, "gzwrite error: %s (error code: %d)\n", error_msg, err);
        fprintf(stderr, "Expected to write %d bytes, but wrote %d bytes\n", len, ret);
        printf("DEBUG: About to call gzclose due to partial write...\n");
        gzclose(out);
        printf("DEBUG: gzclose completed, returning -1\n");
        return -1;
    }
    printf("DEBUG: Condition check - ret != len is FALSE\n");
    printf("Successfully wrote %d bytes\n", ret);
    
    /* Close the file */
    printf("Closing gzip file...\n");
    printf("DEBUG: About to call gzclose...\n");
    int close_ret = gzclose(out);
    printf("DEBUG: gzclose returned %d\n", close_ret);
    
    printf("DEBUG: Checking if gzclose return value != Z_OK (close_ret=%d, Z_OK=%d)...\n", 
           close_ret, Z_OK);
    if (close_ret != Z_OK) {
        printf("DEBUG: Condition check - gzclose != Z_OK is TRUE\n");
        fprintf(stderr, "failed gzclose\n");
        printf("DEBUG: Returning -1 due to gzclose failure\n");
        return -1;
    }
    printf("DEBUG: Condition check - gzclose != Z_OK is FALSE\n");
    printf("Successfully closed file\n");
    
    printf("Test completed successfully\n");
    printf("DEBUG: About to return 0 (success)\n");
    printf("=== DEBUG: Test execution completed successfully ===\n");
    return 0;
}