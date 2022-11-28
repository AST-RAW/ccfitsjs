#pragma once

#include <napi.h>
#include <FITS.h>

class Fits : public Napi::ObjectWrap<Fits> {
  public:
    Fits(const Napi::CallbackInfo&);

    static void GetClass(Napi::Env, Napi::Object exports);
    static Napi::Object NewInstance(Napi::Value arg);

    Napi::Value Load(const Napi::CallbackInfo&);

  private:
    Napi::ThreadSafeFunction _tsfn;
    static Napi::FunctionReference constructor;

    CCfits::FITS *_fits;
};