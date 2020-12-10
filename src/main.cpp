#include "common.h"
#include <stdexcept>
#include <sys/statvfs.h>
#include <errno.h>
#include <string.h>
#include <nan.h>

static v8::Local<v8::Object> Convertstatvfs(const struct statvfs *buf)
{
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();
    Nan::Set(obj, Nan::New<v8::String>("f_bsize").ToLocalChecked(), Nan::New<v8::Number>(static_cast<double>(buf->f_bsize)));
    Nan::Set(obj, Nan::New<v8::String>("f_blocks").ToLocalChecked(), Nan::New<v8::Number>(static_cast<double>(buf->f_blocks)));
    Nan::Set(obj, Nan::New<v8::String>("f_bfree").ToLocalChecked(), Nan::New<v8::Number>(static_cast<double>(buf->f_bfree)));
    Nan::Set(obj, Nan::New<v8::String>("f_bavail").ToLocalChecked(), Nan::New<v8::Number>(static_cast<double>(buf->f_bavail)));
    Nan::Set(obj, Nan::New<v8::String>("f_files").ToLocalChecked(), Nan::New<v8::Number>(static_cast<double>(buf->f_files)));
    Nan::Set(obj, Nan::New<v8::String>("f_ffree").ToLocalChecked(), Nan::New<v8::Number>(static_cast<double>(buf->f_ffree)));
    Nan::Set(obj, Nan::New<v8::String>("f_favail").ToLocalChecked(), Nan::New<v8::Number>(static_cast<double>(buf->f_favail)));
    Nan::Set(obj, Nan::New<v8::String>("f_fsid").ToLocalChecked(), Nan::New<v8::Number>(static_cast<double>(buf->f_fsid)));
    Nan::Set(obj, Nan::New<v8::String>("f_namemax").ToLocalChecked(), Nan::New<v8::Number>(static_cast<double>(buf->f_namemax)));
    Nan::Set(obj, Nan::New<v8::String>("f_frsize").ToLocalChecked(), Nan::New<v8::Number>(static_cast<double>(buf->f_frsize)));
    Nan::Set(obj, Nan::New<v8::String>("f_flag").ToLocalChecked(), Nan::New<v8::Number>(static_cast<double>(buf->f_flag)));
    return obj;
}

static v8::Local<v8::Value> ConvertSystemError(const SystemError& error)
{
    return Nan::ErrnoException(error.errorno(), error.syscall(), error.message(), error.path());
}

static NAN_METHOD(Getstatvfs)
{
    Nan::HandleScope scope;

    try {
	    struct statvfs buf;
        int result = statvfs(*Nan::Utf8String(info[0]), &buf);
        if (result == 0) {
            info.GetReturnValue().Set(Convertstatvfs(&buf));
        }
        else {
            char message[1024];
            snprintf(message, 1024, "statvfs error %i", result);
            Nan::ThrowError(Nan::Error(message)); 
        }
    }
    catch (const SystemError &error) {
        Nan::ThrowError(ConvertSystemError(error));
    }
    catch (const std::exception &ex) {
        Nan::ThrowError(ex.what());
    }
}


void Init(v8::Local<v8::Object> exports)
{
    Nan::SetMethod(exports, "statvfs", Getstatvfs);
}

NODE_MODULE(statvfs, Init)
