#pragma once

#include "promise.h"
#include <FITS.h>
#include <napi.h>

class Fits : public Napi::ObjectWrap<Fits> {
  public:
    Fits(const Napi::CallbackInfo&);

    static void GetClass(Napi::Env, Napi::Object exports);
    static Napi::Object NewInstance(Napi::Value arg);

    Napi::Value Open(const Napi::CallbackInfo&);
    Napi::Value PHDU(const Napi::CallbackInfo&);

  private:
    static Napi::FunctionReference constructor;

    class OpenWorker;
    class PHDUWorker;

    CCfits::FITS* _fits;
    std::string _filename;
};

class Fits::OpenWorker : public PromiseWorker {
  public:
    OpenWorker(Napi::Env env, std::string filename, CCfits::FITS** fits)
        : PromiseWorker(env), _filename(filename), _fits(fits){};

    void Execute();
    Napi::Value GetResolve();
    // Napi::Value GetReject(const Napi::Error& e);

  private:
    std::string _filename;
    CCfits::FITS** _fits;
};

class Fits::PHDUWorker : public PromiseWorker {
  public:
    PHDUWorker(Napi::Env env, CCfits::FITS* fits)
        : PromiseWorker(env), _fits(fits){};

    void Execute();
    Napi::Value GetResolve();
    // Napi::Value GetReject(const Napi::Error& e);

  private:
    CCfits::FITS* _fits;
    CCfits::PHDU* _phdu;
};