extern crate inotify;

use std::path::PathBuf;

use inotify::{
    WatchMask,
    Inotify,
};


fn main() {
    let mut inotify = Inotify::init().expect("Failed to initialize inotify");
    for _i in 0..100 {
        let wd = inotify.add_watch(
            PathBuf::from("/vagrant_data/target"),
            WatchMask::CREATE | WatchMask::DELETE,
        ).expect("Failed to add inotify watch");

        inotify.rm_watch(wd).expect("Failed to remove inotify watch");
    }
}
