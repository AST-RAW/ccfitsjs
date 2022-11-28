#pragma once

#include <HDU.h>
#include <napi.h>

class Hdu : public Napi::ObjectWrap<Hdu> {
  public:
    Hdu(const Napi::CallbackInfo&);
    static void GetClass(Napi::Env, Napi::Object);
    static Napi::Object NewInstance(Napi::Value);

    Napi::Value Axes(const Napi::CallbackInfo&);
    Napi::Value Bitpix(const Napi::CallbackInfo&);
    Napi::Value Comment(const Napi::CallbackInfo&);
    Napi::Value KeyWord(const Napi::CallbackInfo&);

  private:
    static Napi::FunctionReference constructor;
    CCfits::HDU* _hdu;
};

/*

  //return Napi::String::New(env, phdu.getComments());
  //return Napi::Number::New(env, phdu.bitpix());
  //return info.Env().Undefined();
  /*/