#include "hdu.h"

Napi::FunctionReference Hdu::constructor;

Hdu::Hdu(const Napi::CallbackInfo& info) : ObjectWrap(info) {
    Napi::Env env = info.Env();

    if (info.Length() != 1) {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return;
    }

    _hdu = info[0].As<Napi::External<CCfits::PHDU>>().Data();
}

void Hdu::GetClass(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "Hdu",
        {
            Hdu::InstanceMethod("axes", &Hdu::Axes),
            Hdu::InstanceMethod("bitpix", &Hdu::Bitpix),
            Hdu::InstanceMethod("comment", &Hdu::Comment),
            Hdu::InstanceMethod("keyWord", &Hdu::KeyWord),
            Hdu::InstanceMethod("read", &Hdu::Read),
        });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
}

Napi::Object Hdu::NewInstance(Napi::Value arg) {
    Napi::Object obj = constructor.New({arg});
    return obj;
}

Napi::Value Hdu::Axes(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Array array = Napi::Array::New(env);

    for (int i = 0; i < this->_hdu->axes(); i++) {
        array.Set(i, Napi::Number::New(env, this->_hdu->axis(i)));
    }

    return array;
}

Napi::Value Hdu::Bitpix(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    return Napi::Number::New(env, this->_hdu->bitpix());
}

Napi::Value Hdu::Comment(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    return Napi::String::New(env, this->_hdu->getComments());
}

Napi::Value Hdu::KeyWord(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    // Napi::Array array = Napi::Array::New(env);
    Napi::Object obj = Napi::Object::New(env);

    this->_hdu->readAllKeys(); // TODO: async

    std::map<CCfits::String, CCfits::Keyword*> kw = this->_hdu->keyWord();
    // int i = 0;
    for (const auto& [key, value] : kw) {
        switch (value->keytype()) {
            case CCfits::Tint:
                int tval;
                value->value(tval);
                obj.Set(key, tval);
                break;
            case CCfits::Tfloat:
                float fval;
                value->value(fval);
                obj.Set(key, fval);
                break;
            case CCfits::Tdouble:
                double dval;
                value->value(dval);
                obj.Set(key, dval);
                break;
            case CCfits::Tstring:
            default:
                string sval;
                value->value(sval);
                obj.Set(key, sval);
                break;
        }
    }

    return obj;
}

Napi::Value Hdu::Read(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::valarray<unsigned short> data;
    this->_hdu->readAllKeys();
    this->_hdu->read(data);

    return Napi::Buffer<unsigned short>::Copy(env, static_cast<unsigned short*>(&data[0]), data.size());
}