const native = require("./build/Release/statvfs.node");

exports.statvfs = function(path, callback) {
  return statvfs(path, callback);
};

exports.statvfsAsync = function(path) {
  return new Promise(function (resolve, reject) {
    statvfs(path, function (err, result) {
      err ? reject(err) : resolve(result);
    });
  });
}

exports.statvfsSync = native.statvfs;

function statvfs(path, callback) {
  var result = undefined;
  var error = undefined;

  try {
    result = native.statvfs(path);
  } catch (error_) {
    error = error_;
  }

  callback(error, result);
}
