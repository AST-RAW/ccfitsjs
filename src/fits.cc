#include "fits.h"
#include "hdu.h"
#include <CCfits>

Napi::FunctionReference Fits::constructor;

Fits::Fits(const Napi::CallbackInfo& info) : ObjectWrap(info) {
    Napi::Env env = info.Env();

    if (info.Length() != 1) {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return;
    }

    if (!info[0].IsString()) {
        Napi::TypeError::New(env, "You need to set the filename").ThrowAsJavaScriptException();
        return;
    }

    this->_filename = info[0].As<Napi::String>().Utf8Value().c_str();
}

void Fits::GetClass(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "Fits",
        {
            InstanceMethod("load", &Fits::Load),
        });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("Fits", func);
}

Napi::Object Fits::NewInstance(Napi::Value arg) {
    Napi::Object obj = constructor.New({arg});
    return obj;
}

Napi::Value Fits::Load(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    this->_fits = new CCfits::FITS(this->_filename, CCfits::Read, true);
    CCfits::PHDU& phdu = this->_fits->pHDU();
    
    return Hdu::NewInstance(Napi::External<CCfits::PHDU>::New(env, &phdu));
}