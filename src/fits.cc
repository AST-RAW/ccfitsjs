#include "fits.h"
#include "hdu.h"
#include <CCfits>

Napi::FunctionReference Fits::constructor;

Fits::Fits(const Napi::CallbackInfo& info) : ObjectWrap(info) {

}

void Fits::GetClass(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "Fits",
        {
            InstanceMethod("load", &Fits::Load),
            /*InstanceMethod("connect", &IndiClient::Connect),
            InstanceMethod("disconnect", &IndiClient::Disconnect),
            InstanceAccessor("connected", &IndiClient::IsConnected, nullptr),
            InstanceMethod("watchDevice", &IndiClient::WatchDevice),
            InstanceMethod("setBLOBMode", &IndiClient::SetBLOBMode),
            InstanceMethod("getDevice", &IndiClient::GetDevice),
            InstanceMethod("getDevices", &IndiClient::GetDevices),
            InstanceMethod("connectDevice", &IndiClient::ConnectDevice),
            InstanceMethod("sendNewNumber", &IndiClient::SendNewNumber),
            InstanceMethod("sendNewSwitch", &IndiClient::SendNewSwitch),
            InstanceMethod("sendNewText", &IndiClient::SendNewText),*/
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
  this->_fits = new CCfits::FITS("./fits/test.fits", CCfits::Read, true);

  CCfits::PHDU& phdu = this->_fits->pHDU();

  //return Napi::Buffer<char>::Copy(env, static_cast<char*>(getHandle()->blob), getHandle()->bloblen);

  return Hdu::NewInstance(Napi::External<CCfits::PHDU>::New(env, &phdu));
}