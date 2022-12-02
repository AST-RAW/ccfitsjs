#pragma once

#include <CCfits>
#include <napi.h>
#include "promise.h"

class Hdu : public Napi::ObjectWrap<Hdu> {
  public:
    Hdu(const Napi::CallbackInfo&);
    static void GetClass(Napi::Env, Napi::Object);
    static Napi::Object NewInstance(Napi::Value);

    Napi::Value Axes(const Napi::CallbackInfo&);
    Napi::Value Bitpix(const Napi::CallbackInfo&);
    Napi::Value Comment(const Napi::CallbackInfo&);
    Napi::Value KeyWord(const Napi::CallbackInfo&);
    Napi::Value Read(const Napi::CallbackInfo&);
    Napi::Value PHDU(const Napi::CallbackInfo&);

  private:
    class ReadWorker;

    static Napi::FunctionReference constructor;
    CCfits::PHDU* _hdu;
};

class Hdu::ReadWorker : public PromiseWorker {
  public:
    ReadWorker(Napi::Env env, CCfits::PHDU* phdu) : PromiseWorker(env), _phdu(phdu){};

    void Execute();
    Napi::Value GetResolve();
    // Napi::Value GetReject(const Napi::Error& e);

  private:
    CCfits::PHDU* _phdu;
    std::valarray<unsigned short> _data;
};