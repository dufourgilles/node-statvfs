node-statvfs
==============

This module implements statvfs function call

Installation
------------

Install with `npm`:

``` bash
npm install statvfs
```

Usage
--------

The module exposes 3 functions.

- `statvfs(path, callback)`: path should be a string and callback a function that takes an error and a statvfs object.
- `statvfsAsync(path)`: returns a promise to return a statvfs object.
- `statvfsSync(path)`: returns a statvfs object.

Those functions may throw errors containing the standards statvfs error code.

Examples
--------

``` js
const {statvfs, statvfsAsync, statvfsSync } = require('node-statvfs');

// Callbacks
statvfs("/", (err, info) => {
    if (err) {
        console.log(err);
    }
    else {
        console.log(info);
    }
});

// Promise
async function getStat(path) {
  try {
    const info = await statvfsAsync(path);
    console.log(`blocks: ${info.f_blocks}`);
    return info
  } catch (err) {
    console.error(err)
    return 0
  }
}

statvfsAsync("/")
  .then(info => console.log(info))
  .catch(err => console.error(err))

// Synchronous
try {
  const info = statvfsSync("/");
  console.log(info);
}
catch (err) {
  console.log(err);
}
```

TypeScript
----------

The module has an embedded .d.ts file.

Output
------

``` bash
{ f_bsize: 4096,
  f_blocks: 475584404,
  f_bfree: 469772396,
  f_bavail: 450430908,
  f_files: 120799232,
  f_ffree: 120335422,
  f_favail: 120335422,
  f_fsid: 10784525436013701000,
  f_namemax: 255,
  f_frsize: 4096,
  f_flag: 4096 }
```
