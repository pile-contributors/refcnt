class RefCnt {
private:
    int ref_cnt_;
protected:
    RefCnt();
    virtual ~RefCnt();
public:
    int referenceCount() {
        return ref_cnt_;
    }
    void acquire() {
        ++ref_cnt_;
    }
    void release() {
        if (--ref_cnt_ <= 0) {
            delete this;
        }
    }
    void forceRelease() {
        delete this;
    }

};
