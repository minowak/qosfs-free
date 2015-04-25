#include "qosfs.hh"

QoSFS* QoSFS::_instance = NULL;

#define RETURN_ERRNO(x) (x) == 0 ? 0 : -errno

QoSFS* QoSFS::Instance() 
{
        if(_instance == NULL) 
        {
                _instance = new QoSFS();
        }
        return _instance;
}

XAttrs * QoSFS::_xattrs = new XAttrs();

QoSFS::QoSFS() 
{

}

QoSFS::~QoSFS() 
{

}

void QoSFS::AbsPath(char dest[PATH_MAX], const char *path) 
{
        strcpy(dest, _root);
        strncat(dest, path, PATH_MAX);
}

void QoSFS::setRootDir(const char *path) 
{
        printf("[QoSFS] Setting FS root to: %s\n", path);
        _root = path;
}

int QoSFS::Getattr(const char *path, struct stat *statbuf) 
{
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        printf("[QoSFS] getattr(%s)\n", fullPath);
        
        return RETURN_ERRNO(lstat(fullPath, statbuf));
}

int QoSFS::Readlink(const char *path, char *link, size_t size) 
{
        printf("readlink(path=%s, link=%s, size=%d)\n", path, link, (int)size);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        
        return RETURN_ERRNO(readlink(fullPath, link, size));
}

int QoSFS::Mknod(const char *path, mode_t mode, dev_t dev) 
{
        printf("[QoSFS] mknod(path=%s, mode=%d)\n", path, mode);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);

        return RETURN_ERRNO(mknod(fullPath, mode, dev));
}

int QoSFS::Mkdir(const char *path, mode_t mode) 
{
        printf("[QoSFS] **mkdir(path=%s, mode=%d)\n", path, (int)mode);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        
        return RETURN_ERRNO(mkdir(fullPath, mode));
}

int QoSFS::Unlink(const char *path) 
{
        printf("[QoSFS] unlink(path=%s\n)", path);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        
        return RETURN_ERRNO(unlink(fullPath));
}

int QoSFS::Rmdir(const char *path) 
{
        printf("[QoSFS] rmkdir(path=%s\n)", path);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        
        return RETURN_ERRNO(rmdir(fullPath));
}

int QoSFS::Symlink(const char *path, const char *link) 
{
        printf("[QoSFS] symlink(path=%s, link=%s)\n", path, link);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        
        return RETURN_ERRNO(symlink(fullPath, link));
}

int QoSFS::Rename(const char *path, const char *newpath) 
{
        printf("[QoSFS] rename(path=%s, newPath=%s)\n", path, newpath);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        
        return RETURN_ERRNO(rename(fullPath, newpath));
}

int QoSFS::Link(const char *path, const char *newpath) 
{
        printf("[QoSFS] link(path=%s, newPath=%s)\n", path, newpath);
        char fullPath[PATH_MAX];
        char fullNewPath[PATH_MAX];
        AbsPath(fullPath, path);
        AbsPath(fullNewPath, newpath);
        
        return RETURN_ERRNO(link(fullPath, fullNewPath));
}

int QoSFS::Chmod(const char *path, mode_t mode) 
{
        printf("[QoSFS] chmod(path=%s, mode=%d)\n", path, mode);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);

        return RETURN_ERRNO(chmod(fullPath, mode));
}

int QoSFS::Chown(const char *path, uid_t uid, gid_t gid) 
{
        printf("[QoSFS] chown(path=%s, uid=%d, gid=%d)\n", path, (int)uid, (int)gid);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        
        return RETURN_ERRNO(chown(fullPath, uid, gid));
}

int QoSFS::Truncate(const char *path, off_t newSize) 
{
        printf("[QoSFS] truncate(path=%s, newSize=%d\n", path, (int)newSize);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);

        return RETURN_ERRNO(truncate(fullPath, newSize));
}

int QoSFS::Utime(const char *path, struct utimbuf *ubuf) 
{
        printf("[QoSFS] utime(path=%s)\n", path);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        
        return RETURN_ERRNO(utime(fullPath, ubuf));
}

int QoSFS::Open(const char *path, struct fuse_file_info *fileInfo) 
{
        printf("[QoSFS] open(path=%s)\n", path);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        fileInfo->fh = open(fullPath, fileInfo->flags);
        
        return 0;
}

int QoSFS::Read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fileInfo) 
{
        printf("[QoSFS] read(path=%s, size=%d, offset=%d)\n", path, (int)size, (int)offset);
        
        return RETURN_ERRNO(pread(fileInfo->fh, buf, size, offset));
}

int QoSFS::Write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fileInfo) 
{
        printf("[QoSFS] write(path=%s, size=%d, offset=%d)\n", path, (int)size, (int)offset);
        
        return RETURN_ERRNO(pwrite(fileInfo->fh, buf, size, offset));
}

int QoSFS::Statfs(const char *path, struct statvfs *statInfo) 
{
        printf("[QoSFS] statfs(path=%s)\n", path);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        
        return RETURN_ERRNO(statvfs(fullPath, statInfo));
}

int QoSFS::Flush(const char *path, struct fuse_file_info *fileInfo) 
{
        printf("[QoSFS] flush(path=%s)\n", path);
        return 0;
}

int QoSFS::Release(const char *path, struct fuse_file_info *fileInfo) 
{
        printf("[QoSFS] release(path=%s)\n", path);
        return 0;
}

int QoSFS::Fsync(const char *path, int datasync, struct fuse_file_info *fi) 
{
        printf("[QoSFS] fsync(path=%s, datasync=%d\n", path, datasync);
        if(datasync) {
                return RETURN_ERRNO(fdatasync(fi->fh));
        } else {
                return RETURN_ERRNO(fsync(fi->fh));
        }
}

int QoSFS::Setxattr(const char *path, const char *name, const char *value, size_t size, int flags) 
{
        printf("[QoSFS] setxattr(path=%s, name=%s, value=%s, size=%d, flags=%d\n", path, name, value, (int)size, flags);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        
        return _xattrs->SaveXAttr(fullPath, name, value);
}

int QoSFS::Getxattr(const char *path, const char *name, char *value, size_t size) 
{
        printf("[QoSFS] getxattr(path=%s, name=%s, size=%d\n", path, name, (int)size);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        
        string v = _xattrs->GetXAttr(fullPath, name);
        if(value != NULL)
        {
                strcpy(value, v.c_str());
                printf("[QoSFS] value set to %s, needed bytes: %d\n", value, v.size());
        }
 
        return v.size();
}

int QoSFS::Listxattr(const char *path, char *list, size_t size) 
{
        printf("[QoSFS] listxattr(path=%s, size=%d)\n", path, (int)size);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        
        string v = _xattrs->ListXAttr(fullPath);
        int count = _xattrs->GetXAttrCount(fullPath);
        int result = v.size() + count - 1;
        printf("[QoSFS] value is %s\n", v.c_str());
        if(list != NULL)
        {
                strcpy(list, v.c_str());
                printf("[QoSFS] value is set to %s, needed bytes: %d\n", list, result);
        }
        
        return result;
}

int QoSFS::Removexattr(const char *path, const char *name) 
{
        printf("[QoSFS] removexattry(path=%s, name=%s)\n", path, name);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        
        return RETURN_ERRNO(lremovexattr(fullPath, name));
}

int QoSFS::Opendir(const char *path, struct fuse_file_info *fileInfo) 
{
        printf("[QoSFS] opendir(path=%s)\n", path);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        DIR *dir = opendir(fullPath);
        fileInfo->fh = (uint64_t)dir;
        
        return NULL == dir ? -errno : 0;
}

int QoSFS::Readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fileInfo) 
{
        printf("[QoSFS] readdir(path=%s, offset=%d)\n", path, (int)offset);
        DIR *dir = (DIR*)fileInfo->fh;
        struct dirent *de = readdir(dir);
        if(NULL == de) 
        {
                return -errno;
        } else 
        {
                do 
                {
                        if(filler(buf, de->d_name, NULL, 0) != 0) 
                                return -ENOMEM;
                } while(NULL != (de = readdir(dir)));
        }
        
        return 0;
}

int QoSFS::Releasedir(const char *path, struct fuse_file_info *fileInfo) 
{
        printf("[QoSFS] releasedir(path=%s)\n", path);
        closedir((DIR*)fileInfo->fh);
        
        return 0;
}

int QoSFS::Fsyncdir(const char *path, int datasync, struct fuse_file_info *fileInfo) 
{
        return 0;
}

int QoSFS::Init(struct fuse_conn_info *conn) 
{
        return 0;
}

int QoSFS::Truncate(const char *path, off_t offset, struct fuse_file_info *fileInfo) 
{
        printf("[QoSFS] truncate(path=%s, offset=%d)\n", path, (int)offset);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        
        return RETURN_ERRNO(ftruncate(fileInfo->fh, offset));
}



