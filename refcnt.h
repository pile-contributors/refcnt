class RefCnt {
private:
    int ref_cnt_;
protected:
    RefCnt();
    virtual ~RefCnt();
public:
    void acquire() {
        ++ref_cnt_;
    }
    void release() {
        if (--ref_cnt_ <= 0) {
            delete this;
        }
    }
};
