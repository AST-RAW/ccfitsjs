#include "fits.h"
#include "hdu.h"
#include <CCfits>

Napi::FunctionReference Fits::constructor;

Fits::Fits(const Napi::CallbackInfo& info) : ObjectWrap(info), _fits(nullptr) {
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

Napi::Value Fits::Open(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    OpenWorker* wk = new OpenWorker(env, this->_filename, &this->_fits);

    wk->Queue();

    return wk->Deferred().Promise();
}

Napi::Value Fits::PHDU(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    PHDUWorker* wk = new PHDUWorker(env, this->_fits);

    wk->Queue();

    return wk->Deferred().Promise();
}

// static methods

void Fits::GetClass(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "Fits",
        {
            InstanceMethod("open", &Fits::Open),
            InstanceMethod("pHDU", &Fits::PHDU),
        });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("Fits", func);
}

Napi::Object Fits::NewInstance(Napi::Value arg) {
    Napi::Object obj = constructor.New({arg});
    return obj;
}

// worker implementations

void Fits::OpenWorker::Execute() {
    try {
        *this->_fits = new CCfits::FITS(this->_filename, CCfits::Read, false);
    } catch (const CCfits::FitsException &e) {
        this->SetError(e.message());
    }
}

Napi::Value Fits::OpenWorker::GetResolve() {
    return Napi::Boolean::New(Env(), true);
}

void Fits::PHDUWorker::Execute() {
    CCfits::PHDU& phdu = this->_fits->pHDU();
    this->_phdu = &phdu;
}

Napi::Value Fits::PHDUWorker::GetResolve() {
    return Hdu::NewInstance(Napi::External<CCfits::PHDU>::New(Env(), this->_phdu));
}
