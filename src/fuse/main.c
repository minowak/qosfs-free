#include "wrap.hh"

#include <fuse.h>
#include <stdio.h>

struct fuse_operations qosfs_oper;

int main(int argc, char *argv[]) 
{
        int i, fuse_stat;
        
        qosfs_oper.getattr = wrap_getattr;
        qosfs_oper.readlink = wrap_readlink;
        qosfs_oper.getdir = NULL;
        qosfs_oper.mknod = wrap_mknod;
        qosfs_oper.mkdir = wrap_mkdir;
        qosfs_oper.unlink = wrap_unlink;
        qosfs_oper.rmdir = wrap_rmdir;
        qosfs_oper.symlink = wrap_symlink;
        qosfs_oper.rename = wrap_rename;
        qosfs_oper.link = wrap_link;
        qosfs_oper.chmod = wrap_chmod;
        qosfs_oper.chown = wrap_chown;
        qosfs_oper.truncate = wrap_truncate;
        qosfs_oper.utime = wrap_utime;
        qosfs_oper.open = wrap_open;
        qosfs_oper.read = wrap_read;
        qosfs_oper.write = wrap_write;
        qosfs_oper.statfs = wrap_statfs;
        qosfs_oper.flush = wrap_flush;
        qosfs_oper.release = wrap_release;
        qosfs_oper.fsync = wrap_fsync;
        qosfs_oper.setxattr = wrap_setxattr;
        qosfs_oper.getxattr = wrap_getxattr;
        qosfs_oper.listxattr = wrap_listxattr;
        qosfs_oper.removexattr = wrap_removexattr;
        qosfs_oper.opendir = wrap_opendir;
        qosfs_oper.readdir = wrap_readdir;
        qosfs_oper.releasedir = wrap_releasedir;
        qosfs_oper.fsyncdir = wrap_fsyncdir;
        qosfs_oper.init = wrap_init;

        printf("[QoSFS] Mounting QoSFS ...\n");
        
        for(i = 1; i < argc && (argv[i][0] == '-'); i++) 
        {
                if(i == argc) 
                {        
                        return (-1);
                }
        }

        set_rootdir(realpath(argv[i], NULL));

        for(; i < argc; i++) 
        {
                argv[i] = argv[i+1];
        }
        argc--;

        fuse_stat = fuse_main(argc, argv, &qosfs_oper, NULL);

        printf("[QoSFS] fuse_main returned %d\n", fuse_stat);

        return fuse_stat;
}



