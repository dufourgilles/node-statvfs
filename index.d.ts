type StatsFS = {
    f_bsize: number;   /* Optimal transfer block size */
    f_blocks: number;  /* Total data blocks in filesystem */
    f_bfree: number;   /* Free blocks in filesystem */
    f_bavail: number;  /* Free blocks available to
                                        unprivileged user */
    f_files: number;   /* Total file nodes in filesystem */
    f_ffree: number;   /* Free file nodes in filesystem */
    f_favail: number;   /* Number of free inodes for unprivileged users */
    f_fsid: number;    /* Filesystem ID */
    f_namemax: number; /* Maximum length of filenames */
    f_frsize: number;  /* Fragment size (since Linux 2.6) */
    f_flag: number;   /* Mount flags */
}


export function statvfs(path: string, callback: (error?: Error, result?: StatsFS) => void): void;
export function statvfsAsync(path: string): Promise<StatsFS>
export function statvfsSync(path: string): StatsFS;