$Id: README.txt,v 1.1 2009/02/13 19:24:06 bdziewierz Exp $ 

role_expire.module implements the following functionality:
- Selecting a role (or roles) on user_profile_form triggers a textfield (or textfields) where admins can enter expire date for selected role(s).
- Defined expiry dates are displayed on user's profile (visible only for owners of the profile or users with proper permissions). This can be altered using standard theme_ or hook_user() functions.
- Role expiry dates are controlled by Cron, so it automatically removes any expired roles from affected users.
- Simple API is provided to set, clear or retrieve expiry dates for given roles and users. 
- Views.module handlers are provided for displaying, sorting and filtering expiry dates inside views (per role).