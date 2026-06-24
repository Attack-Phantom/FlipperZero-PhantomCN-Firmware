#include <core/dangerous_defines.h>
#include <furi.h>
#include <storage/storage.h>

#include "animation_storage.h"
#include "animation_storage_i.h"
#include "bad_apple.h"
#include <momentum/momentum.h>

#define BAD_APPLE_NAME "BadApple"
#define BAD_APPLE_DIR ASSET_PACKS_PATH "/PhantomCN/Anims/BadApple"
#define BAD_APPLE_MANIFEST ASSET_PACKS_PATH "/PhantomCN/Anims/manifest.txt"
#define BAD_APPLE_FRAMES 120
#define BAD_APPLE_W 128
#define BAD_APPLE_H 64
#define BAD_APPLE_RATE 24
#define BAD_APPLE_DURATION 3600
#define BAD_APPLE_MAX_BYTES (24 * 1024)

static bool bad_apple_sd_ready(Storage* storage) {
    return (storage_sd_status(storage) == FSE_OK) &&
           (storage_common_stat(storage, BAD_APPLE_MANIFEST, NULL) == FSE_OK);
}

static StorageAnimation* bad_apple_sd_alloc(void) {
    StorageAnimation* item = malloc(sizeof(StorageAnimation));
    if(!item) return NULL;

    item->animation = NULL;
    item->external = true;
    item->manifest_info.name = strdup(BAD_APPLE_NAME);
    if(!item->manifest_info.name) {
        free(item);
        return NULL;
    }

    item->manifest_info.min_butthurt = 0;
    item->manifest_info.max_butthurt = 255;
    item->manifest_info.min_level = 1;
    item->manifest_info.max_level = 30;
    item->manifest_info.weight = 255;

    return item;
}

static void bad_apple_free(BubbleAnimation* animation) {
    if(!animation) return;

    const uint8_t* const* frames = animation->icon_animation.frames;
    if(frames) {
        for(uint8_t i = 0; i < animation->icon_animation.frame_count; i++) {
            free((void*)frames[i]);
        }
        free((void*)frames);
    }

    free((void*)animation->frame_order);
    free(animation);
}

static bool bad_apple_read_frame(Storage* storage, uint8_t frame, uint8_t** data, size_t* total) {
    char path[sizeof(BAD_APPLE_DIR) + sizeof("/frame_119.bm")];
    snprintf(path, sizeof(path), "%s/frame_%u.bm", BAD_APPLE_DIR, frame);

    FileInfo info;
    if(storage_common_stat(storage, path, &info) != FSE_OK) return false;
    if(file_info_is_dir(&info) || !info.size || info.size > 512) return false;
    if((*total + info.size) > BAD_APPLE_MAX_BYTES) return false;

    File* file = storage_file_alloc(storage);
    if(!file) return false;

    bool ok = false;
    uint8_t* buf = malloc(info.size);
    do {
        if(!buf) break;
        if(!storage_file_open(file, path, FSAM_READ, FSOM_OPEN_EXISTING)) break;
        if(storage_file_read(file, buf, info.size) != info.size) break;

        *data = buf;
        *total += info.size;
        ok = true;
    } while(false);

    storage_file_free(file);
    if(!ok) free(buf);
    return ok;
}

static BubbleAnimation* bad_apple_load_sd(void) {
    Storage* storage = furi_record_open(RECORD_STORAGE);
    if(!bad_apple_sd_ready(storage)) {
        furi_record_close(RECORD_STORAGE);
        return NULL;
    }

    BubbleAnimation* animation = malloc(sizeof(BubbleAnimation));
    const uint8_t** frames = malloc(sizeof(uint8_t*) * BAD_APPLE_FRAMES);
    uint8_t* order = malloc(BAD_APPLE_FRAMES);
    bool ok = animation && frames && order;

    if(ok) {
        memset(animation, 0, sizeof(BubbleAnimation));
        memset(frames, 0, sizeof(uint8_t*) * BAD_APPLE_FRAMES);
        for(uint8_t i = 0; i < BAD_APPLE_FRAMES; i++) {
            order[i] = i;
        }

        FURI_CONST_ASSIGN(animation->icon_animation.width, BAD_APPLE_W);
        FURI_CONST_ASSIGN(animation->icon_animation.height, BAD_APPLE_H);
        FURI_CONST_ASSIGN(animation->icon_animation.frame_count, BAD_APPLE_FRAMES);
        FURI_CONST_ASSIGN(animation->icon_animation.frame_rate, BAD_APPLE_RATE);
        FURI_CONST_ASSIGN_PTR(animation->icon_animation.frames, frames);
        FURI_CONST_ASSIGN_PTR(animation->frame_order, order);

        animation->passive_frames = BAD_APPLE_FRAMES;
        animation->active_frames = 0;
        animation->active_cycles = 0;
        animation->duration = BAD_APPLE_DURATION;
        animation->active_cooldown = 5;

        size_t total = 0;
        for(uint8_t i = 0; i < BAD_APPLE_FRAMES; i++) {
            uint8_t* frame = NULL;
            if(!bad_apple_read_frame(storage, i, &frame, &total)) {
                ok = false;
                break;
            }
            FURI_CONST_ASSIGN_PTR(animation->icon_animation.frames[i], frame);
        }
    }

    furi_record_close(RECORD_STORAGE);

    if(!ok) {
        if(animation) {
            FURI_CONST_ASSIGN_PTR(animation->icon_animation.frames, frames);
            FURI_CONST_ASSIGN_PTR(animation->frame_order, order);
            bad_apple_free(animation);
        } else {
            if(frames) free(frames);
            if(order) free(order);
        }
        return NULL;
    }

    return animation;
}

void animation_storage_fill_animation_list(StorageAnimationList_t* animation_list) {
    furi_assert(sizeof(StorageAnimationList_t) == sizeof(void*));
    furi_assert(!StorageAnimationList_size(*animation_list));

    Storage* storage = furi_record_open(RECORD_STORAGE);
    StorageAnimation* item = bad_apple_sd_ready(storage) ? bad_apple_sd_alloc() : NULL;
    furi_record_close(RECORD_STORAGE);

    StorageAnimationList_push_back(
        *animation_list, item ? item : (StorageAnimation*)&bad_apple_animation);
}

StorageAnimation* animation_storage_find_animation(const char* name) {
    furi_assert(name);
    if(strcmp(name, BAD_APPLE_NAME)) return NULL;

    Storage* storage = furi_record_open(RECORD_STORAGE);
    StorageAnimation* item = bad_apple_sd_ready(storage) ? bad_apple_sd_alloc() : NULL;
    furi_record_close(RECORD_STORAGE);

    return item ? item : (StorageAnimation*)&bad_apple_animation;
}

StorageAnimationManifestInfo* animation_storage_get_meta(StorageAnimation* storage_animation) {
    furi_assert(storage_animation);
    return &storage_animation->manifest_info;
}

const BubbleAnimation* animation_storage_get_bubble_animation(StorageAnimation* storage_animation) {
    furi_assert(storage_animation);
    animation_storage_cache_animation(storage_animation);
    return storage_animation->animation ? storage_animation->animation : bad_apple_animation.animation;
}

void animation_storage_cache_animation(StorageAnimation* storage_animation) {
    furi_assert(storage_animation);

    if(storage_animation->external && !storage_animation->animation) {
        BubbleAnimation* animation = bad_apple_load_sd();
        if(animation) {
            storage_animation->animation = animation;
        }
    }
}

void animation_storage_free_storage_animation(StorageAnimation** storage_animation) {
    furi_assert(storage_animation);
    furi_assert(*storage_animation);

    if((*storage_animation)->external) {
        bad_apple_free((BubbleAnimation*)(*storage_animation)->animation);
        free((void*)(*storage_animation)->manifest_info.name);
        free(*storage_animation);
    }

    *storage_animation = NULL;
}

void animation_storage_initialize_internal_animations(void) {
}
